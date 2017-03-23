/**
 * @file
 * LightWeightM2M Project Config.
 *
 * @author Imagination Technologies
 *
 * @copyright Copyright (c) 2016, Imagination Technologies Limited and/or its affiliated group
 * companies and/or licensors.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PROJECT_LWM2M_CONF_H__
#define __PROJECT_LWM2M_CONF_H__

/* Custom channel and PAN ID configuration for your project. */
/*
   #define RF_CHANNEL                  26
   #define IEEE802154_CONF_PANID       0xABCD
 */

/* IP buffer size must match all other hops, in particular the border router. */
/*
   #define UIP_CONF_BUFFER_SIZE        256
 */

/* Disabling RDC and CSMA for demo purposes. Core updates often
   require more memory. */
/* For projects, optimize memory and enable RDC and CSMA again. */
/* Depending upon __USE_CC2520__ or __USE_CA8210__,
   this is defined as nullrdc_driver or nullrdc_noframer_driver ,
   so commenting out from here.
   #define NETSTACK_CONF_RDC              nullrdc_driver
*/
/* Disabling TCP on CoAP nodes. */
#define UIP_CONF_TCP                   0

/*
   #define NETSTACK_CONF_MAC     nullmac_driver
*/

/* Increase rpl-border-router IP-buffer when using more than 64. */
#define REST_MAX_CHUNK_SIZE            512

/* Estimate your header size, especially when using Proxy-Uri. */
/*
   #define COAP_MAX_HEADER_SIZE        70
 */

/* Multiplies with chunk size, be aware of memory constraints. */
#undef COAP_MAX_OPEN_TRANSACTIONS
#define COAP_MAX_OPEN_TRANSACTIONS     4

/* Must be <= open transactions, default is COAP_MAX_OPEN_TRANSACTIONS-1. */
/*
   #define COAP_MAX_OBSERVERS          2
 */

/* Filtering .well-known/core per query can be disabled to save space. */
#define COAP_LINK_FORMAT_FILTERING     0
#define COAP_PROXY_OPTION_PROCESSING   0

/* Enable client-side support for COAP observe */
#define COAP_OBSERVE_CLIENT            1

#define UIP_CONF_TCP                   0

#define UIP_CONF_BUFFER_SIZE           4096

#define GLOBAL_IPv6_ADDR
#define GLOBAL_IPv6_ADDR1              0xfd77
#define GLOBAL_IPv6_ADDR2              0x9c74
#define GLOBAL_IPv6_ADDR3              0xddee
#define GLOBAL_IPv6_ADDR4              0xc0e7
#define GLOBAL_IPv6_ADDR5              0x0
#define GLOBAL_IPv6_ADDR6              0x0
#define GLOBAL_IPv6_ADDR7              0x0
#define GLOBAL_IPv6_ADDR8              0x0


#define RESOLV_CONF_SUPPORTS_MDNS  0

#define BOOTSTRAP_ADDR                 "deviceserver.creatordev.io"
#define DEFAULT_ROUTE_IPv6             "fd77:9c74:ddee:c0e7::1"

#endif /* __PROJECT_LWM2M_CONF_H__ */
