package commands;

import programContent.Content;
/**
 * The command pops two elements off the stack, compares them and
 * puts 1 if first greater or 0 else
 */
public class Greater extends Command {
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("Greater command execute");
        int a = content.pop();
        int b = content.pop();
        content.stack.push(a < b ? 1 : 0);
    }
}
