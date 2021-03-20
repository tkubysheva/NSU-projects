package commands;
import java.util.Scanner;
import programContent.Content;

/**
 * The function that takes a char-value from the user and pushed it onto the stack
 */
public class InputCharacter extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("InputCharacter command execute");

        char n = content.getInputStreamChar();
        content.stack.push((int)n);
        /*
        Scanner in = new Scanner(System.in);
        content.stack.push((int)in.next(".").charAt(0));
*/

    }
}
