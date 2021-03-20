package commands;

import programContent.Content;
/**
 * The command pops two elements off the stack, multiplies
 * them and puts result back on the stack
 */
public class Multiplication extends Command {
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("Multiplication command execute");
        int a = content.pop();
        int b = content.pop();
        content.stack.push(a * b);
    }
}
