package commands;

import programContent.Content;
/**
 * The command that pops a number from the top of the stack
 * and if it is 0 then puts 1 on the stack or 0 otherwise
 */
public class Not extends Command {
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        int a = content.pop();
        content.stack.push(a == 0 ? 1 : 0);
    }
}
