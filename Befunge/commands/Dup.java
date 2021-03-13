package commands;

import programContent.Content;
/**
 * The command pushed the last element of the stack onto the stack again
 */
public class Dup extends Command {
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        int a = content.pop();
        content.stack.push(a);
        content.stack.push(a);
    }
}
