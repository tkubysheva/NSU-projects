package commands;

import programContent.Content;

public class Pop extends Command{
    @Override
    public void Action(Content content) {
        pop(content.stack);
    }
}
