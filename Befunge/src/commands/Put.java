package commands;

import programContent.Content;

/**
 * The command that takes three values from the top of stack:
 * <y>, <x> and <value> and changes the field of Befunge program
 * value to <value> by coordinates
 */
public class Put extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("Put command execute");
        int y = content.pop();
        int x = content.pop();
        int value = content.pop();
        content.field[y*content.field_x + x] = (char)value;
    }
}
