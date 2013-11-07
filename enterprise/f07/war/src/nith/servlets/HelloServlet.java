package nith.servlets;

import java.io.IOException;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Created with IntelliJ IDEA. User: Martin Date: 11/7/13 Time: 10:42 AM To change this
 * template use File | Settings | File Templates.
 */
public class HelloServlet extends HttpServlet
{
    @EJB
    private nith.beans.HelloBeanBean beanRef;

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
    {
        super.doPost(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
    {
        String answer = beanRef.isOver18(12) ? "YAY!" : "Stay the fuck away.";

        req.setAttribute("message", answer);
        req.getRequestDispatcher("answer.jsp").forward(req, resp);
    }
}
