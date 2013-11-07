import java.io.IOException;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;

/**
 * Created with IntelliJ IDEA. User: Martin Date: 11/7/13 Time: 11:27 AM To change this
 * template use File | Settings | File Templates.
 */
public class HelloServlet extends HttpServlet
{
    @EJB
    private HelloBean beanReference;

    public HelloServlet()
    {
    }

    public boolean isOver18(int age)
    {
        return age >= 18;
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
    {
        String answer = beanReference.isOver18(20) ? "Go for it!" : "Stay away!";

        req.setAttribute("message", answer);
        req.getRequestDispatcher("answer.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
    {
        throw new NotImplementedException();
    }
}
