package commands;
import java.util.Scanner;
import programContent.Content;
/**
 * The command that takes a int-value from the user and pushed it onto the stack
 */
public class InputInt extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        Scanner in = new Scanner(System.in);
        content.stack.push(in.nextInt());
    }
}
