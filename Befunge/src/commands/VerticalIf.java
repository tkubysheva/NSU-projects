package commands;

import programContent.DIRECTION;
import programContent.Content;
/**
 * The command that turns the direction of the movement
 * to the down if the last element of the stack is zero
 * or to the up otherwise
 */
public class VerticalIf extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        log.info("VerticalIf command execute");
        if(content.pop() != 0){
            content.direction = DIRECTION.UP;
        }
        else{
            content.direction = DIRECTION.DOWN;
        }
    }
}
