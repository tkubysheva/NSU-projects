package commands;

import programContent.Content;

/**
 * The command that makes the next command to be skipped
 */
public class Bridge extends Command{
    @Override
    /**
     *
     * @param content {@link programContent.Content}
     */
    protected void action(Content content) {
        log.info("Bridge command execute");
        content.bridge = true;
    }
}
