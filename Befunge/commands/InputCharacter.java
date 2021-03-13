package commands;
import java.util.Scanner;
import programContent.Content;

/**
 * The command that takes a char-value from the user and pushed it onto the stack
 */
public class InputCharacter extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        Scanner in = new Scanner(System.in);
        content.stack.push((int)in.next(".").charAt(0));
    }
}
