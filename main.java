import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

class Ledger {
    int customer_id;
    float customer_balance;
    float customer_credit;
    int customer_poetWaitTime;

    public Ledger(int id) {
        this.customer_id = id;
        this.customer_balance = 50.0f;
        this.customer_credit = 0.0f;
        this.customer_poetWaitTime = -1;
    }
}

public class Main {
    private static final int ARRAY_SIZE = 4;
    private static Ledger[] customers = new Ledger[ARRAY_SIZE];
    private static Random rand = new Random();

    public static void main(String[] args) throws IOException {
        // Initialize the values
        for (int j = 0; j < ARRAY_SIZE; j++) {
            customers[j] = new Ledger(j);
        }

        // Open CSV file for writing output
        FileWriter fout = new FileWriter("Data.csv");
        fout.write("Tick,Customer_id,Transaction type,Balance,Credit\n");

        // Initial value of tick
        int tick = 0;
        // Assume that there is no collision until it's proven true
        boolean collision = false;
        // Initialize the percent
        int y = 20;

        while (true) {
            tick++;
            fout.write(tick + ",");
            int flag = 0;
            // Iterate a loop to check the status of the system
            for (Ledger customer : customers) {
                if (customer.customer_poetWaitTime > 0) {
                    customer.customer_poetWaitTime--;
                    flag = 1;
                } else if (customer.customer_poetWaitTime == 0) {
                    flag = 1;
                }
            }

            // This loop works only when there is no collision
            if (flag == 0) {
                collision = false;
                int s = rand.nextInt(4);
                int t = rand.nextInt(4);
                double f = rand.nextDouble();
                double g = rand.nextDouble();

                if (f > 0.1 && g > 0.1) {
                    collision = true;
                    fout.write("PoET WaitTime\n");
                } else if (g > 0.1) {
                    customers[s].customer_poetWaitTime = 0;
                } else if (f > 0.1) {
                    customers[t].customer_poetWaitTime = 0;
                } else {
                    fout.write("Event has not Occurred\n");
                }

                if (collision) {
                    int poetDelay = rand.nextInt(5);
                    customers[s].customer_poetWaitTime = poetDelay;
                    poetDelay = rand.nextInt(5);
                    customers[t].customer_poetWaitTime = poetDelay;
                }
            }

            // Initialize an array for credit check
            int[] checkCredit = {-1, -1, -1, -1};
            for (int k = 0; k < ARRAY_SIZE; k++) {
                if (checkCredit[k] > 0) {
                    checkCredit[k]--;
                } else if (checkCredit[k] == 0) {
                    // Update the credit by percent
                    customers[k].customer_credit += 0.2 * customers[k].customer_credit;
                    customers[k].customer_balance -= customers[k].customer_credit;
                    customers[k].customer_credit = 0;
                    checkCredit[k] = -1;
                }
            }

            for (int i = 0; i < ARRAY_SIZE; i++) {
                if (customers[i].customer_poetWaitTime == 0) {
                    flag = 0;
                    // Generate a random number for the transaction type
                    int b = rand.nextInt(5);
                    // Generate a random number for the amount
                    int c = rand.nextInt(50);
                    // Generate a random number for customer to use in case of buy/sell
                    int j = rand.nextInt(3);

                    switch (b) {
                        case 0: // Deposit
                            customers[i].customer_balance += c;
                            fout.write((char) (customers[i].customer_id + 65) + ",DEPOSIT," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            break;
                        case 1: // Withdraw
                            if (customers[i].customer_balance >= c) {
                                customers[i].customer_balance -= c;
                                fout.write((char) (customers[i].customer_id + 65) + ",WITHDRAW," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            } else {
                                fout.write((char) (customers[i].customer_id + 65) + ",WITHDRAW-NOT ENOUGH BALANCE," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            }
                            break;
                        case 2: // Buy
                            if (customers[i].customer_balance > customers[i].customer_credit && c <= customers[i].customer_balance) {
                                customers[j].customer_balance += c;
                                customers[i].customer_balance -= c;
                                fout.write((char) (customers[i].customer_id + 65) + ",BUY FROM " + (char) (customers[j].customer_id + 65) + "," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            } else {
                                fout.write((char) (customers[i].customer_id + 65) + ",BUY-NOT ENOUGH BALANCE," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            }
                            break;
                        case 3: // Sell
                            if (c <= customers[j].customer_balance) {
                                customers[i].customer_balance += c;
                                customers[j].customer_balance -= c;
                                fout.write((char) (customers[i].customer_id + 65) + ",SELL TO " + (char) (customers[j].customer_id + 65) + "," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            } else {
                                fout.write((char) (customers[i].customer_id + 65) + ",SELL-NOT POSSIBLE," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            }
                            break;
                        case 4: // Request credit
                            if (customers[i].customer_balance > 0 && customers[i].customer_credit == 0) {
                                customers[i].customer_credit += 0.2 * customers[i].customer_balance;
                                checkCredit[i] = y;
                                fout.write((char) (customers[i].customer_id + 65) + ",REQUEST CREDIT," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            } else {
                                fout.write((char) (customers[i].customer_id + 65) + ",REQUEST CREDIT - CANNOT BE DONE," + customers[i].customer_balance + "," + customers[i].customer_credit + "\n");
                            }
                            break;
                        default: // Null transaction
                            break;
                    }
                    customers[i].customer_poetWaitTime--;
                    break;
                }
            }

            if (flag == 1) {
                fout.write("PoET waitTime\n");
            }

            if (tick >= 1000) {
                break;
            }
        }

        // Close file
        fout.close();
    }
}
