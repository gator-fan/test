/*************************************************************************
 * @File Name: evhttp.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年06月23日 星期二 19时28分26秒
 ************************************************************************/

#include <iostream>
#include <evhttp.h>

using namespace std;

void http_request_handler(struct evhttp_request* req, void *arg)
{
  struct evbuffer *databuf = evbuffer_new();
  evbuffer_add_printf(databuf, "hello world");
  evhttp_send_reply_start(req, 200, "ok");
  evhttp_send_reply_chunk(req, databuf);
  evhttp_send_reply_end(req);

  evbuffer_free(databuf);
}

int main()
{
  struct event_base *base = event_base_new();
  struct evhttp * httpd = evhttp_new(base);
  evhttp_bind_socket(httpd, "0.0.0.0", 19800);
  evhttp_set_gencb(httpd, http_request_handler, NULL);
  event_base_dispatch(base);
}

