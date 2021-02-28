package commands;

import programContent.Content;

public class OutputInt extends Command{

    @Override
    public void Action(Content content) {
        System.out.print(content.stack.pop());
    }
}
