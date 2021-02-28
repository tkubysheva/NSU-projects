package commands;

import programContent.DIR;
import programContent.Content;
import java.util.Random;

public class TurnRandom extends Command {
    @Override
    public void Action(Content content) {
        final Random random = new Random();

        switch (random.nextInt(4)) {
            case 0 -> content.direction = DIR.RIGHT;
            case 1 -> content.direction = DIR.UP;
            case 2 -> content.direction = DIR.LEFT;
            case 3 -> content.direction = DIR.DOWN;
        }
    }
}
