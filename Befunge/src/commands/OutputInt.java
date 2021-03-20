package commands;

import programContent.Content;

/**
 * The command that pops an item off the top of the stack
 * and prints its numeric representation
 */
public class OutputInt extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("OutputInt command execute");
        int n = content.pop();
        content.getOutputStream(n);
    }
}
