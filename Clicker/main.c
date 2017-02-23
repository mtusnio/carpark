#include <stdio.h>

#include <contiki.h>


#include "dev/leds.h"

#include "letmecreate/click/motion.h"
#include "letmecreate/core/common.h"

#include "letmecreate/core/debug.h"

#include "awa/static.h"

#define COAP_PORT 6000
#define BOOTSTRAP_SERVER_URI "coap://[" BOOTSTRAP_IPv6_ADDR "]:15683"

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

static AwaStaticClient * InitialiseAwaClient()
{
    AwaStaticClient * client = AwaStaticClient_New();

    AwaStaticClient_SetLogLevel(AwaLogLevel_Debug);
    AwaStaticClient_SetEndPointName(client, STR(CLIENT_NAME));
    AwaStaticClient_SetCoAPListenAddressPort(client, "::", COAP_PORT);
    AwaStaticClient_SetBootstrapServerURI(client, BOOTSTRAP_SERVER_URI);

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

        ipv6_add_default_route(BOOTSTRAP_IPv6_ADDR, 0);

        awaClient = InitialiseAwaClient();

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
