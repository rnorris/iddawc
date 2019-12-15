/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>

#include <check.h>
#include <yder.h>
#include <iddawc.h>

#define SCOPE1 "scope1"
#define SCOPE2 "scope2"
#define SCOPE_LIST "scope1 scope2"
#define STATE "stateXyz1234"
#define REDIRECT_URI "https://iddawc.tld"
#define REDIRECT_TO "https://iddawc.tld#access_token=plop"
#define CLIENT_ID "clientXyz1234"
#define CLIENT_SECRET "secretXyx1234"
#define AUTH_ENDPOINT "http://localhost:8080/auth"
#define TOKEN_ENDPOINT "https://isp.tld/token"
#define ACCESS_TOKEN_VALIDATION_ENDPOINT "https://isp.tld/profile"
#define CODE "codeXyz1234"
#define REFRESH_TOKEN "refreshXyz1234"
#define ACCESS_TOKEN "accessXyz1234"
#define TOKEN_TYPE "typeXyz1234"
#define EXPIRES_IN 3600
#define ID_TOKEN "idTokenXyz1234"
#define ERROR "errorXyz1234"
#define ERROR_DESCRIPTION "errorDescriptionXyz1234"
#define ERROR_URI "errorUriXyz1234"
#define GLEWLWYD_API_URL "https://glewlwyd.tld/api"
#define GLEWLWYD_COOKIE_SESSION "cookieXyz1234"

int callback_oauth2_unauthorized_public_client (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s?error=unauthorized_client&error_description=Invalid+client_id&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_invalid_scope (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s?error=invalid_scope&error_description=Scope+missing&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_invalid_response_type (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s?error=invalid_request&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_invalid_state (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s?code=xyz&state=error%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_code_empty (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s?code&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_access_token_empty (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#access_token&token_type=" TOKEN_TYPE "&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_token_type_empty (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#access_token=" ACCESS_TOKEN "&token_type&code&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_expires_in_invalid (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#access_token=" ACCESS_TOKEN "&token_type=" TOKEN_TYPE "&expires_in=error&code&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_code_valid (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s?code=" CODE "&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_access_token_valid (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#access_token=" ACCESS_TOKEN "&token_type=" TOKEN_TYPE "&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_id_token_valid (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#id_token=" ID_TOKEN "&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_access_token_id_token_valid (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#access_token=" ACCESS_TOKEN "&id_token=" ID_TOKEN "&token_type=" TOKEN_TYPE "&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_access_token_code_valid (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#access_token=" ACCESS_TOKEN "&code=" CODE "&token_type=" TOKEN_TYPE "&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_access_token_code_id_token_valid (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s#access_token=" ACCESS_TOKEN "&id_token=" ID_TOKEN "&code=" CODE "&token_type=" TOKEN_TYPE "&state=%s", u_map_get(request->map_url, "redirect_url"), u_map_get(request->map_url, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

int callback_oauth2_code_valid_post (const struct _u_request * request, struct _u_response * response, void * user_data) {
  char * redirect = msprintf("%s?code=" CODE "&state=%s", u_map_get(request->map_post_body, "redirect_url"), u_map_get(request->map_post_body, "state"));
  u_map_put(response->map_header, "Location", redirect);
  response->status = 302;
  o_free(redirect);
  return U_CALLBACK_CONTINUE;
}

START_TEST(test_iddawc_unauthorized_public_client)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_unauthorized_public_client, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_int_eq(i_get_result(&i_session), I_ERROR_UNAUTHORIZED);
  ck_assert_str_eq(i_get_parameter(&i_session, I_OPT_ERROR), "unauthorized_client");
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_invalid_client_secret)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_unauthorized_public_client, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_CLIENT_SECRET, CLIENT_SECRET,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_int_eq(i_get_result(&i_session), I_ERROR_UNAUTHORIZED);
  ck_assert_str_eq(i_get_parameter(&i_session, I_OPT_ERROR), "unauthorized_client");
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_scope_empty)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_invalid_scope, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_int_eq(i_get_result(&i_session), I_ERROR_UNAUTHORIZED);
  ck_assert_str_eq(i_get_parameter(&i_session, I_OPT_ERROR), "invalid_scope");
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_invalid_response_type)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_invalid_response_type, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_int_eq(i_get_result(&i_session), I_ERROR_UNAUTHORIZED);
  ck_assert_str_eq(i_get_parameter(&i_session, I_OPT_ERROR), "invalid_request");
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_invalid_state)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_invalid_state, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_ERROR_SERVER);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_code_empty)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_code_empty, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_ERROR_SERVER);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_access_token_empty)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_access_token_empty, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_TOKEN,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_ERROR_SERVER);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_token_type_empty)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_token_type_empty, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_TOKEN,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_ERROR_SERVER);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_expires_in_invalid)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_expires_in_invalid, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_TOKEN,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_ERROR_SERVER);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_code_valid)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_code_valid, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_access_token_valid)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_access_token_valid, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_TOKEN,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_id_token_valid)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_id_token_valid, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_ID_TOKEN,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_ID_TOKEN), NULL);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_ID_TOKEN), NULL);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_access_token_id_token_valid)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_access_token_id_token_valid, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_TOKEN|I_RESPONSE_TYPE_ID_TOKEN,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_ID_TOKEN), NULL);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_ID_TOKEN), NULL);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_access_token_code_valid)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_access_token_code_valid, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_TOKEN|I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_access_token_code_id_token_valid)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "GET", NULL, "/auth", 0, &callback_oauth2_access_token_code_id_token_valid, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_TOKEN|I_RESPONSE_TYPE_CODE|I_RESPONSE_TYPE_ID_TOKEN,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_NONE), I_OK);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_ID_TOKEN), NULL);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_ACCESS_TOKEN), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_TOKEN_TYPE), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_ID_TOKEN), NULL);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

START_TEST(test_iddawc_code_valid_post)
{
  struct _i_session i_session;
  struct _u_instance instance;
  ck_assert_int_eq(i_init_session(&i_session), I_OK);
  ck_assert_int_eq(ulfius_init_instance(&instance, 8080, NULL, NULL), U_OK);
  ck_assert_int_eq(ulfius_add_endpoint_by_val(&instance, "POST", NULL, "/auth", 0, &callback_oauth2_code_valid_post, NULL), U_OK);
  ck_assert_int_eq(ulfius_start_framework(&instance), U_OK);
  ck_assert_int_eq(i_set_parameter_list(&i_session, I_OPT_RESPONSE_TYPE, I_RESPONSE_TYPE_CODE,
                                                  I_OPT_CLIENT_ID, CLIENT_ID,
                                                  I_OPT_REDIRECT_URI, REDIRECT_URI,
                                                  I_OPT_SCOPE, SCOPE_LIST,
                                                  I_OPT_AUTH_ENDPOINT, AUTH_ENDPOINT,
                                                  I_OPT_STATE, STATE,
                                                  I_OPT_AUTH_METHOD, I_AUTH_METHOD_POST,
                                                  I_OPT_NONE), I_OK);
  ck_assert_ptr_eq(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  ck_assert_int_eq(i_run_auth_request(&i_session), I_OK);
  ck_assert_ptr_ne(i_get_parameter(&i_session, I_OPT_CODE), NULL);
  
  i_clean_session(&i_session);
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
}
END_TEST

static Suite *ulfius_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Iddawc oauth2 flow tests");
  tc_core = tcase_create("test_iddawc_oauth2");
  tcase_add_test(tc_core, test_iddawc_unauthorized_public_client);
  tcase_add_test(tc_core, test_iddawc_invalid_client_secret);
  tcase_add_test(tc_core, test_iddawc_scope_empty);
  tcase_add_test(tc_core, test_iddawc_invalid_response_type);
  tcase_add_test(tc_core, test_iddawc_invalid_state);
  tcase_add_test(tc_core, test_iddawc_code_empty);
  tcase_add_test(tc_core, test_iddawc_access_token_empty);
  tcase_add_test(tc_core, test_iddawc_token_type_empty);
  tcase_add_test(tc_core, test_iddawc_expires_in_invalid);
  tcase_add_test(tc_core, test_iddawc_code_valid);
  tcase_add_test(tc_core, test_iddawc_access_token_valid);
  tcase_add_test(tc_core, test_iddawc_id_token_valid);
  tcase_add_test(tc_core, test_iddawc_access_token_id_token_valid);
  tcase_add_test(tc_core, test_iddawc_access_token_code_valid);
  tcase_add_test(tc_core, test_iddawc_access_token_code_id_token_valid);
  tcase_add_test(tc_core, test_iddawc_code_valid_post);
  tcase_set_timeout(tc_core, 30);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  y_init_logs("Iddawc", Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_DEBUG, NULL, "Starting Iddawc OAuth2 flow tests");
  s = ulfius_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  
  y_close_logs();
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}