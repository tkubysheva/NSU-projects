package commands;
import programContent.Content;

public class InStack extends Command{
    @Override
    public void Action(Content content) {
        if(Character.isLetter(content.inStack)){
            content.stack.push((int) content.inStack);
        }
        else if(Character.isDigit(content.inStack)){
            content.stack.push(Character.getNumericValue(content.inStack));
        }
    }
}
