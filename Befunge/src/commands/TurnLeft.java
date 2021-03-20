package commands;
import programContent.DIRECTION;
import programContent.Content;
/**
 * The command that turns the direction of the movement
 * to the left
 */
public class TurnLeft extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("TurnLeft command execute");
        content.direction = DIRECTION.LEFT;
    }
}
