import java.io.*;
import java.util.*;
import org.apache.commons.math3.stat.inference.*;
import org.apache.commons.math3.stat.descriptive.DescriptiveStatistics;

public class FootballStats {

    //----------------------------Declarations-------------------------------------------------------------------

    public static final int NUMBER_OF_TEAMS = 32;
    public static ArrayList<String> teams = new ArrayList<>();
    public static ArrayList<Double> asm = new ArrayList<>();
    public static ArrayList<Double> py = new ArrayList<>();
    public static ArrayList<Double> dpy = new ArrayList<>();
    public static ArrayList<Double> ry = new ArrayList<>();
    public static ArrayList<Double> dry = new ArrayList<>();
    public static ArrayList<Double> to = new ArrayList<>();
    public static ArrayList<Double> dto = new ArrayList<>();
    public static ArrayList<Double> pendif = new ArrayList<>();
    public static ArrayList<Double> rettd = new ArrayList<>();
    public static ArrayList<Double> psm = new ArrayList<>();
    public static String line = null;
    private DescriptiveStatistics statsASM = new DescriptiveStatistics();
    private DescriptiveStatistics statsPSM = new DescriptiveStatistics();
    private TTest ttest = new TTest();
    private double[] sample1 = new double[NUMBER_OF_TEAMS];
    private double[] sample2 = new double[NUMBER_OF_TEAMS];

    //---------------------------Main function-------------------------------------------------------------------

    public static void main(String [] args) {
        FootballStats test = new FootballStats();
        test.readFileAndParse();
        test.calculateTeamStats();
        test.printTeamStats();
    }

    //-------------This function will read and parse text file "teamStats.txt" into teamName & teamData----------

    public void readFileAndParse(){

        String fileName = "teamStats.txt";

        try {
            FileReader fileReader = new FileReader(fileName);
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            while((line = bufferedReader.readLine()) != null) {
                String [] teamName = line.split("\\|");             //Split team name from rest data.
                String [] teamsData = teamName[1].split(" ");       //Split name of rest Data from team name.

                //Store each team name into ArrayList of "teams"
                String individualTeamName = teamName[0];
                teams.add(individualTeamName);

                //Store each data value for each team into their respective Array List. Such as asm for all teams are stored in ArrayList "asm"
                for(int i = 1; i<teamsData.length;i++){
                    double aDouble = Double.parseDouble(teamsData[i]);    //Convert string into double so we can apply Mathematic calculation on it.

                    if(i == 1)
                        asm.add(aDouble);
                    else if(i == 2)
                        py.add(aDouble);
                    else if(i == 3)
                        dpy.add(aDouble);
                    else if(i== 4)
                        ry.add(aDouble);
                    else if(i== 5)
                        dry.add(aDouble);
                    else if(i== 6)
                        to.add(aDouble);
                    else if(i== 7)
                        dto.add(aDouble);
                    else if(i== 8)
                        pendif.add(aDouble);
                    else if(i== 9)
                        rettd.add(aDouble);
                    else
                        System.out.println("Error in Storing Data ! \n");
                }
            }
            bufferedReader.close();
        }

        catch(FileNotFoundException ex) {
            System.out.println(
                    "Unable to open file '" +        //give error if unable to open given file.
                            fileName + "'");
        }
        catch(IOException ex) {
            System.out.println(
                    "Error reading file '"           //give error if there is problem in reading given file.
                            + fileName + "'");
        }
    }

    //-------------This function will calculate PSM and store ASM PSM into sample1[] sample2[] for tTest.

    public void calculateTeamStats() {

        for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
            double ans = 3.17 * (rettd.get(i)) - 0.06 * (pendif.get(i)) + 61.67 * (py.get(i)) + 26.44 * (ry.get(i)) - 2.77 * (to.get(i)) - 67.5 * (dpy.get(i)) - 22.79 * (dry.get(i)) + 3.49 * (dto.get(i));
            psm.add(ans);
            sample1[i] = asm.get(i);
            sample2[i] = psm.get(i);
            statsASM.addValue(sample1[i]);
            statsPSM.addValue(sample2[i]);
        }
    }

    //--------------This function will print all the output data in my program.-----------------------------------

    public void printTeamStats() {

        System.out.println("|-----------------------------------------------------------------------------------------------------------------------|");
        System.out.println("|----------TEAM NAME----------------------------------ASM------------------------------------------PSM------------------|");
        System.out.println("|-----------------------------------------------------------------------------------------------------------------------|");

        for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
            if (i == 0)
                System.out.println("\nNFC East:");
            else if (i == 4)
                System.out.println("\nNFC West:");
            else if (i == 8)
                System.out.println("\nNFC North:");
            else if (i == 12)
                System.out.println("\nNFC South:");
            else if (i == 16)
                System.out.println("\nAFC East:");
            else if (i == 20)
                System.out.println("\nAFC West:");
            else if (i == 24)
                System.out.println("\nAFC North:");
            else if (i == 28)
                System.out.println("\nAFC South:");

            System.out.printf("%22s", teams.get(i));
            System.out.printf("%36.2f", asm.get(i));
            System.out.printf("%45.2f \n", psm.get(i));
        }
        System.out.println("|-----------------------------------------------------------------------------------------------------------------------|");
        System.out.printf("\nSample Size : %25s", NUMBER_OF_TEAMS);
        System.out.printf("\nT-Test (ASM vs PSM) : %17.4f ", ttest.t(sample1, sample2));
        System.out.printf("\n\nMean of ASM : %25.4f ", statsASM.getMean());
        System.out.printf("\nStandard Deviation of ASM : %11.4f ", statsASM.getStandardDeviation());
        System.out.printf("\nMax of ASM : %26.4f ", statsASM.getMax());
        System.out.printf("\nMin of ASM : %26.4f ", statsASM.getMin());
        System.out.printf("\n\nMean of PSM : %25.4f ", statsPSM.getMean());
        System.out.printf("\nStandard Deviation of PSM : %11.4f ", statsPSM.getStandardDeviation());
        System.out.printf("\nMax of PSM : %26.4f ", statsPSM.getMax());
        System.out.printf("\nMin of PSM : %26.4f ", statsPSM.getMin());
    }
}

//-----------------------END OF PROGRAM--------------------------------------------------------------------------------