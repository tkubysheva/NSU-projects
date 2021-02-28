package commands;

import programContent.DIR;
import programContent.Content;

public class HorizontalIf extends Command{
    @Override
    public void Action(Content content) {
        if(pop(content.stack) != 0){
            content.direction = DIR.LEFT;
        }
        else{
            content.direction = DIR.RIGHT;
        }
    }
}
