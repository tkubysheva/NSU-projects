package commands;

import programContent.Content;

public class Bridge extends Command{
    @Override
    public void Action(Content content) {
        content.bridge = true;
    }
}
