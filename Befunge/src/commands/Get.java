package commands;

import programContent.Content;

/**
 * The command that gets the top of the stack two elements x and y,
 * and puts on the stack the value at these coordinates
 */
public class Get extends Command {
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("Get command execute");
        int y = content.pop();
        int x = content.pop();
        content.stack.push((int)content.field[y* content.field_x +x]);
    }
}
