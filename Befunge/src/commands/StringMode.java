package commands;

import programContent.Content;

/**
 * The command that turns on the line mode
 */
public class StringMode extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("StringMode command execute");
        content.stringMode = !content.stringMode;
    }
}
