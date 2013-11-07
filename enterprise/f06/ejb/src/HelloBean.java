import javax.ejb.Stateless;

/**
 * Created with IntelliJ IDEA.
 * User: Martin
 * Date: 11/7/13
 * Time: 11:28 AM
 * To change this template use File | Settings | File Templates.
 */
@Stateless(name = "HelloEJB")
public class HelloBean {
    public HelloBean() {
    }

    public boolean isOver18(int age) {
        return age >= 18;
    }
}
