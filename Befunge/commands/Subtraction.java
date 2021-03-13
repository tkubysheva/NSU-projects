package commands;

import programContent.Content;
/**
 * The command pops two elements off the stack, subtracts the first
 * by the second them and puts result back on the stack
 */
public class Subtraction extends Command {
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        int a = content.pop();
        int b = content.pop();
        content.stack.push(b - a);
    }
}
