import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Peer {
    public static ExecutorService executor = Executors.newFixedThreadPool(3);

    public static void main(String[] args) {
        Runnable serverTask = new Runnable() {
            @Override
            public void run() {
                Server server = new Server(Integer.parseInt(args[1]));
            }
        };

        Runnable clientTask = new Runnable() {
            @Override
            public void run() {

                Client client = new Client(Integer.parseInt(args[1]), args[2], args);
            }
        };

        if (args[0].equals("server")) {
            executor.submit(serverTask);
        } else if (args[0].equals("peer")) {
            executor.submit(serverTask);
            executor.submit(clientTask);
        }
    }
}