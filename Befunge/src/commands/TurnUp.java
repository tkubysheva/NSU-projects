package commands;
import programContent.Content;
import programContent.DIRECTION;
/**
 * The command that turns the direction of the movement
 * to the up
 */
public class TurnUp extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("TurnUp command execute");
        content.direction = DIRECTION.UP;
    }
}
