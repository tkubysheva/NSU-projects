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
        log.info("InStack command execute");
        content.stack.push((int) content.inStack);
    }
}
