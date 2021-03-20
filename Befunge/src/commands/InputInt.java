package commands;
import java.io.InputStream;
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
        log.info("InputInt command execute");
        int n = content.getInputStreamInt();
        content.stack.push(n);
    }
}
