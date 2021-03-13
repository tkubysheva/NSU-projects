package commands;
import programContent.DIRECTION;
import programContent.Content;
/**
 * The command that turns the direction of the movement
 * to the down
 */
public class TurnDown extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        content.direction = DIRECTION.DOWN;
    }
}
