#include <stdio.h>

#include <contiki.h>


#include "dev/leds.h"

#include "letmecreate/click/motion.h"
#include "letmecreate/core/common.h"

#include "letmecreate/core/debug.h"

#include "awa/static.h"

#define COAP_PORT 6000
#define BOOTSTRAP_SERVER_URI "coaps://" BOOTSTRAP_ADDR ":15684"

#define STR(s) _STR(s)
#define _STR(s) #s

#define CARDETECTOR_OBJECT 10241
#define CARDETECTOR_RESOURCE 1
#define CARDETECTOR_NAME "CarDetector"
#define CARDETECTOR_RESOURCE_NAME "Motion"

typedef struct
{
    int CarStatus;
} ParkingSpot;


static ParkingSpot spot;
static AwaStaticClient * awaClient = NULL;

uint8_t secret[sizeof(STR(SECRET))/2];


static int StringToBytes(const char * hex, uint8_t * secret)
{
    int i;

    if(secret == NULL) {
        fprintf(stderr, "Null bytes array\n");
        return -1;
    }

    if(hex == NULL) {
        fprintf(stderr, "Null hex string\n");
        return -1;
    }

    if(strlen(hex) % 2 != 0) {
        fprintf(stderr, "String length is not divisible by two\n");
        return -1;
    }

    for(i = 0; i < strlen(hex); i += 2) {
        char byte_string[3] = { hex[i], hex[i+1], '\0' };
        secret[i/2] = (uint8_t)strtol(byte_string, NULL, 16);
    }

    return 0;
}

static AwaStaticClient * InitialiseAwaClient()
{
    if(StringToBytes(STR(SECRET), secret) != 0) {
        fprintf(stderr, "Failed to convert the PSK\n");
        return NULL;
    }

    AwaStaticClient * client = AwaStaticClient_New();

    AwaStaticClient_SetLogLevel(AwaLogLevel_Debug);
    AwaStaticClient_SetEndPointName(client, STR(CLIENT_NAME));
    AwaStaticClient_SetCoAPListenAddressPort(client, "::", COAP_PORT);
    AwaStaticClient_SetBootstrapServerURI(client, BOOTSTRAP_SERVER_URI);
    AwaStaticClient_SetPSK(client, STR(IDENTITY), secret, sizeof(secret));

    AwaStaticClient_Init(client);

    return client;
}

static void DefineObjects(AwaStaticClient * client)
{
    AwaStaticClient_DefineObject(client, CARDETECTOR_OBJECT, CARDETECTOR_NAME, 0, 1);
    AwaStaticClient_DefineResource(client, CARDETECTOR_OBJECT, CARDETECTOR_RESOURCE,
                                    CARDETECTOR_RESOURCE_NAME, AwaResourceType_Integer,
                                    0, 1, AwaResourceOperations_ReadOnly);
    AwaStaticClient_SetResourceStorageWithPointer(client, CARDETECTOR_OBJECT,
                    CARDETECTOR_RESOURCE, &spot.CarStatus, sizeof(spot.CarStatus), sizeof(spot));
}

static void SetInitialValues(AwaStaticClient * client)
{
    AwaStaticClient_CreateObjectInstance(client, CARDETECTOR_OBJECT, 0);
    AwaStaticClient_CreateResource(client, CARDETECTOR_OBJECT, 0, CARDETECTOR_RESOURCE);
    spot.CarStatus = 0;
}



static void motion_callback(uint8_t event)
{
    spot.CarStatus = (spot.CarStatus == 1) ? 0 : 1;
    leds_toggle(LED1);

    AwaStaticClient_ResourceChanged(awaClient, CARDETECTOR_OBJECT, 0, CARDETECTOR_RESOURCE);
}


PROCESS(main_process, "Main process");
AUTOSTART_PROCESSES(&main_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
    PROCESS_BEGIN();
    INIT_NETWORK_DEBUG();
    {
        PRINTF("=====Start=====\n");

        ipv6_add_default_route(DEFAULT_ROUTE_IPv6, NETWORK_INFINITE_LIFETIME);
        ipv6_add_nameserver(DEFAULT_ROUTE_IPv6, NETWORK_INFINITE_LIFETIME);

        awaClient = InitialiseAwaClient();

        if(!awaClient) {
            fprintf(stderr, "Awa client not initialised\n");
            return -1;
        }

        DefineObjects(awaClient);
        SetInitialValues(awaClient);

        motion_click_enable(MIKROBUS_1);


        static struct etimer et;

        motion_click_attach_callback(MIKROBUS_1, motion_callback);
        while(1)
        {
            AwaStaticClient_Process(awaClient);

            etimer_set(&et, CLOCK_SECOND / 4);
            PROCESS_YIELD();
        }

        motion_click_disable(MIKROBUS_1);
    }

    PROCESS_END();
}

/*---------------------------------------------------------------------------*/
