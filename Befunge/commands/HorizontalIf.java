package commands;
import programContent.Content;
import programContent.DIRECTION;

/**
 * The command that turns the direction of the movement
 * to the right if the last element of the stack is zero
 * or to the left otherwise
 */
public class HorizontalIf extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        if(content.pop() != 0){
            content.direction = DIRECTION.LEFT;
        }
        else{
            content.direction = DIRECTION.RIGHT;
        }
    }
}
