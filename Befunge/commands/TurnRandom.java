package commands;

import programContent.DIRECTION;
import programContent.Content;
import java.util.Random;
/**
 * The command that turns the direction of the movement
 * to the random direction
 */
public class TurnRandom extends Command {
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        final Random random = new Random();

        switch (random.nextInt(4)) {
            case 0 -> content.direction = DIRECTION.RIGHT;
            case 1 -> content.direction = DIRECTION.UP;
            case 2 -> content.direction = DIRECTION.LEFT;
            case 3 -> content.direction = DIRECTION.DOWN;
        }
    }
}
