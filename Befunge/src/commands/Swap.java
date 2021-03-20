package commands;

import programContent.Content;
/**
 * The command pops two elements off the stack, swaps
 * them and puts result back on the stack
 */
public class Swap extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("Swap command execute");
        int a = content.pop();
        int b = content.pop();
        content.stack.push(a);
        content.stack.push(b);
    }
}
