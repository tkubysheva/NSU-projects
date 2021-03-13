package commands;
import programContent.DIRECTION;
import programContent.Content;

/**
 * The command that stops the program
 */
public class End extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        content.direction = DIRECTION.END;
    }
}
