package commands;

import programContent.Content;

/**
 * The command that pops an item off the top of stack
 */
public class Pop extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        content.pop();
    }
}
