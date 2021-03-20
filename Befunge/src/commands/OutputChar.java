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
        log.info("OutputChar command execute");
        int n = content.pop();
        content.getOutputStream((char)n);
    }
}
