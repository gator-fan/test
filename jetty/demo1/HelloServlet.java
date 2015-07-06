/*************************************************************************
 * @File Name: HelloServlet.java
 * @Author: wangfan
 * @Mail: wangfan@mediav.com 
 * @Created Time: 2015年03月26日 星期四 18时30分20秒
 ************************************************************************/
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;

import java.io.IOException;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class HelloServlet extends AbstractHandler
{
	public void handle(String target,
						Request baseRequest,
						HttpServletRequest request,
						HttpServletResponse response)
		throws IOException, ServletException
	{
		response.setContentType("text/html;charset=utf-8");
		response.setStatus(HttpServletResponse.SC_OK);
		baseRequest.setHandled(true);
		response.getWriter().println("<h1>Hello Servlet</h1>");
	}

	public static void main(String[] args) throws Exception
	{
		Server server = new Server(8080);
		server.setHandler(new HelloServlet());

		server.start();
		server.join();
	}
}
