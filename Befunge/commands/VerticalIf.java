package commands;

import programContent.DIR;
import programContent.Content;

public class VerticalIf extends Command{
    @Override
    public void Action(Content content) {
        if(pop(content.stack) != 0){
            content.direction = DIR.UP;
        }
        else{
            content.direction = DIR.DOWN;
        }
    }
}
