package commands;
import programContent.DIR;
import programContent.Content;

public class TurnLeft extends Command{
    @Override
    public void Action(Content content) {
        content.direction = DIR.LEFT;
    }
}
