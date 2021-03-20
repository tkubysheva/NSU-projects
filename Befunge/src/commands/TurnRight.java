package commands;
import programContent.Content;
import programContent.DIRECTION;
/**
 * The command that turns the direction of the movement
 * to the right
 */
public class TurnRight extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("TurnRight command execute");
        content.direction = DIRECTION.RIGHT;
    }
}
