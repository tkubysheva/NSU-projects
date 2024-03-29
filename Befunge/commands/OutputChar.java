package commands;

import programContent.Content;

/**
 * The command that pops an item off the top of the stack
 * and prints its ascii character
 */
public class OutputChar extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        System.out.print((char)(int) content.stack.pop());
    }
}
