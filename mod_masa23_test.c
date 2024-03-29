/* 
**  mod_masa23_test.c -- Apache sample masa23_test module
**  [Autogenerated via ``apxs -n masa23_test -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_masa23_test.c
**
**  Then activate it in Apache's httpd.conf file for instance
**  for the URL /masa23_test in as follows:
**
**    #   httpd.conf
**    LoadModule masa23_test_module modules/mod_masa23_test.so
**    <Location /masa23_test>
**    SetHandler masa23_test
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /masa23_test and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/masa23_test 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_masa23_test.c
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "http_log.h"

module AP_MODULE_DECLARE_DATA masa23_test_module;

typedef struct {
    int Enabled;
    char* String;
} Masa23TestConfig;

/* The sample content handler */
static int masa23_test_handler(request_rec *r)
{
    Masa23TestConfig *conf;
    conf = (Masa23TestConfig *)ap_get_module_config(r->server->module_config,
                                                    &masa23_test_module);
    
    if (strcmp(r->handler, "masa23_test")) {
        return DECLINED;
    }
    r->content_type = "text/plain";      

    if (!r->header_only){
    if(conf->Enabled){
            ap_rputs("mod_masa23_test enabled\n", r);
            ap_rputs(conf->String, r);
    }else{
            ap_rputs("mod_masa23_test disalbed\n", r);
            ap_rputs(conf->String, r);
        }
    }
    return OK;
}

static void masa23_test_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(masa23_test_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

static void *create_masa23_test_server_config(apr_pool_t *p, server_rec *s)
{
    Masa23TestConfig *conf = apr_pcalloc(p, sizeof *conf);
    conf->Enabled = 0;
    conf->String = "masa23";

    return conf;
}

static const char *masa23_test_on(cmd_parms *cmd, void *dummy, int arg)
{
    Masa23TestConfig *conf = ap_get_module_config(cmd->server->module_config,
                                                  &masa23_test_module);
    conf->Enabled = arg;

    return NULL;
}

static const char *add_masa23_string(cmd_parms *cmd, void *dummy,
                                     char *arg)
{
    Masa23TestConfig *conf = ap_get_module_config(cmd->server->module_config,
                                                  &masa23_test_module);
    conf->String = arg;

    return NULL;
}

static const command_rec masa23_test_cmds[] =
{
    AP_INIT_FLAG("Masa23Test", masa23_test_on, NULL, RSRC_CONF,
                 "mod_masa23_test enabled on/off"),
    AP_INIT_ITERATE("Masa23String", add_masa23_string, NULL, RSRC_CONF,
                    "mod_masa23_test string config"),
    { NULL }
};


/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA masa23_test_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                             /* create per-dir    config structures */
    NULL,                             /* merge  per-dir    config structures */
    create_masa23_test_server_config, /* create per-server config structures */
    NULL,                             /* merge  per-server config structures */
    masa23_test_cmds,                 /* table of config file commands       */
    masa23_test_register_hooks        /* register hooks                      */
};

