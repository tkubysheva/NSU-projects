package commands;
import programContent.Content;
/**
 * The command that pushed number from the field onto the stack
 */
public class InStack extends Command{
    /**
     *
     * @param content {@link programContent.Content}
     */
    @Override
    protected void action(Content content) {
        if(Character.isLetter(content.inStack)){
            content.stack.push((int) content.inStack);
        }
        else if(Character.isDigit(content.inStack)){
            content.stack.push(Character.getNumericValue(content.inStack));
        }
    }
}
