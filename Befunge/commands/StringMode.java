package commands;

import programContent.Content;

public class StringMode extends Command{
    @Override
    public void Action(Content content) {
        content.stringMode = !content.stringMode;
    }
}
