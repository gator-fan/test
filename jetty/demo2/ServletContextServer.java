/*************************************************************************
 * @File Name: ServletContextServer.java
 * @Author: wangfan
 * @Mail: wangfan@mediav.com 
 * @Created Time: 2015年03月26日 星期四 17时25分26秒
 ************************************************************************/
package myweb;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class ServletContextServer {
	public static void main(String[] args) throws Exception
	{
		Server server = new Server(8080);

		ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
		context.setContextPath("/");
		server.setHandler(context);

		context.addServlet(new ServletHolder(new HelloServlet()), "/hello");
		context.addServlet(new ServletHolder(new HelloServlet("Hello Gator!")), "/hello/gator");

		context.addServlet(new ServletHolder(new GoodbyeServlet()), "/goodbye");
		context.addServlet(new ServletHolder(new GoodbyeServlet("Goodbye Gator!")), "/goodbye/gator!!!");

		server.start();
		server.join();
	}
}
