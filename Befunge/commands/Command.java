package commands;
import programContent.Content;

/**
 * Abstract command class
 */
public abstract class Command {
    /**
     *Function that performs command action
     * @param content {@link programContent.Content}
     */
    protected abstract void action(Content content);

    /**
     *The function that trigger the action
     * @param content {@link programContent.Content}
     */
    public void execute(Content content){
        if(content.bridge){
            content.bridge = false;
            return;
        }
        action(content);
    }
}
