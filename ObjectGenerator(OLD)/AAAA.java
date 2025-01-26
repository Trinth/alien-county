import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.IOException;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.border.Border;


public class Main extends JFrame implements ActionListener
{

    class Date{
        public int Day = 1;
        public int Month = 1;
        public int Year = 1970;

        public Date(int Day, int Month, int Year){
            this.Day = Day;
            this.Month = Month;
            this.Year = Year;

        }

    }

    class Task{

        public String name;

        public String description;

        public LocalDate Start;
        public LocalDate End;


        public Task(String Name, String description, LocalDate Start, LocalDate End){
            this.name = Name;
            this.description = description;
            this.Start = Start;
            this.End = End;
        }

    }

    ArrayList<Task> tasks;

    Scanner scanner;

    private  JPanel MainPanel;

    int ShownTasks = 5;

    class TaskGUI{
        private JLabel name;
        private JLabel description;
        private JLabel Start;
        private JLabel End;

        public TaskGUI(JLabel name, JLabel description, JLabel Start, JLabel End){
            this.name = name;
            this.description = description;
            this.Start = Start;
            this.End = End;
        }


    }



    private JMenuItem Save, Load;

    private JMenuItem Add, Delete;

    private JTextArea TaskTextArea;

    private JFrame frame;

    private JFrame popupFrame;

    PopupMenu popupMenu;

    int TaskToDelete = 0;

    private TaskInputDialog InputDialog;

    public void Main(){
        tasks = new ArrayList<>();
        LoadAll();


        //Creating the Frame
        frame = new JFrame("Adiministrador de tareas");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);

        JMenuBar menuBar = new JMenuBar();

        JMenu MainMenu = new JMenu("Archivo");

        JMenu TaskMenu = new JMenu("Tareas");


        Add = new JMenuItem("Añadir");
        Add.addActionListener(this);
        TaskMenu.add(Add);

        Delete = new JMenuItem("Eliminar");
        Delete.addActionListener(this);
        TaskMenu.add(Delete);


        Save = new JMenuItem("Guardar");
        Save.addActionListener(this);
        MainMenu.add(Save);

        Load = new JMenuItem("Recargar");
        Load.addActionListener(this);
        MainMenu.add(Load);


        menuBar.add(MainMenu);
        menuBar.add(TaskMenu);


        TaskTextArea = new JTextArea();
        TaskTextArea.setBounds(10,50,400,300);
        TaskTextArea.setEditable(false);

        ReDrawText();
        DateTimeFormatter myFormatObj = DateTimeFormatter.ofPattern("dd-MM-yyyy");


        JScrollPane scroll = new JScrollPane (TaskTextArea,
        JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        frame.add(scroll);



        frame.getContentPane().add(BorderLayout.NORTH, menuBar);
        frame.setVisible(true);

        InputDialog = new TaskInputDialog(frame,true);



    }
    public void ReDrawText(){
        DateTimeFormatter myFormatObj = DateTimeFormatter.ofPattern("dd-MM-yyyy");
        TaskTextArea.setText("");
        if(tasks.size() <= 0){
            TaskTextArea.append("No hay tareas");
        }
        else{
            for(int i = 0; i < tasks.size(); i ++){
               /* TaskTextArea.append("--------------------------------------------------------------------------------------------------------");
                TaskTextArea.append("--------------------------------------------------------------------------------------------------------");
                TaskTextArea.append("--------------------------------------------------------------------------------------------------------");*/
                //TaskTextArea.append("\n");
                TaskTextArea.append( "Tarea: " + (i + 1) + "\n" );

                TaskTextArea.append("Titulo: " + tasks.get(i).name + "\n");
                TaskTextArea.append("Descripción: " + tasks.get(i).description + "\n");

                TaskTextArea.append("Fecha inicial: " + tasks.get(i).Start.format(myFormatObj) + "\n");
                TaskTextArea.append("Fecha final: " + tasks.get(i).End.format(myFormatObj) + "\n");
                TaskTextArea.append("\n");
              /*  TaskTextArea.append("--------------------------------------------------------------------------------------------");
                TaskTextArea.append("--------------------------------------------------------------------------------------------------------");
                TaskTextArea.append("--------------------------------------------------------------------------------------------------------");*/

            }
        }
       // TaskTextArea.setText("");
    }


    void AddTaskVerbose(String title, String description, LocalDate start, LocalDate end){
         tasks.add(new Task(title, description,start,end));
    }


    public class TaskInputDialog extends JDialog{

        public TaskInputDialog(JFrame father, boolean modal) {
            super(father,modal);
            this.initGUI();
        }

        private void initGUI() {

            this.setLocation(400,200);
            this.setSize(500,500);
            this.setLayout(null);


            JButton boton = new JButton("Close");
            JDialog self = this;

            JButton Save = new JButton("Guardar");

            JButton StartDate = new JButton("Fecha inicial");

            JButton EndDate = new JButton("Fecha final");

            Save.setBounds(15,443,470,20);
            this.add(Save);


            Border Border = BorderFactory.createLineBorder(Color.BLACK);

            JTextArea TaskNameTextArea = new JTextArea();
            TaskNameTextArea.setBounds(15,112,470,40);
            this.add(TaskNameTextArea);
            TaskNameTextArea.setBorder(BorderFactory.createCompoundBorder(Border,BorderFactory.createEmptyBorder(5, 5, 5, 5)));

            JTextArea TaskDescriptionTextArea = new JTextArea();
            TaskDescriptionTextArea.setBounds(15,176,470,255);
            this.add(TaskDescriptionTextArea);
            TaskDescriptionTextArea.setBorder(BorderFactory.createCompoundBorder(Border,BorderFactory.createEmptyBorder(5, 5, 5, 5)));




            JSpinner DayStart = new JSpinner(new SpinnerNumberModel(1, 1, 31, 1));
            DayStart.setBounds(149, 13, 96, 43);
            this.add(DayStart);

            JSpinner MonthStart = new JSpinner(new SpinnerNumberModel(1, 1, 12, 1));
            MonthStart.setBounds(251, 13, 96, 43);
            this.add(MonthStart);

            JSpinner YearStart = new JSpinner();
            YearStart.setValue(2024);
            YearStart.setBounds(358, 13, 127, 43);
            this.add(YearStart);



            JSpinner DayEnd = new JSpinner(new SpinnerNumberModel(1, 1, 31, 1));
            DayEnd.setBounds(149, 62, 96, 43);
            this.add(DayEnd);

            JSpinner MonthEnd = new JSpinner(new SpinnerNumberModel(1, 1, 12, 1));
            MonthEnd.setBounds(251, 62, 96, 43);
            this.add(MonthEnd);

            JSpinner YearEnd = new JSpinner();
            YearEnd.setValue(2024);
            YearEnd.setBounds(358, 62, 127, 43);
            this.add(YearEnd);

            JLabel StartDateLabel = new JLabel("Fecha inicial");
            StartDateLabel.setBounds(15, 13, 128, 43);
            this.add(StartDateLabel);

            JLabel EndDateLabel = new JLabel("Fecha final");
            EndDateLabel.setBounds(15, 62, 128, 43);
            this.add(EndDateLabel);


            boton.addActionListener(new ActionListener() {

                @Override
                public void actionPerformed(ActionEvent e) {
                    ((TaskInputDialog) self).closeDialog();
                }

            });

            Save.addActionListener(new ActionListener() {

                @Override
                public void actionPerformed(ActionEvent e) {

                    String day = new String();
                    String month = new String();
                    String year = new String();

                    day = String.valueOf(DayStart.getValue());
                    month = String.valueOf(MonthStart.getValue());
                    year = String.valueOf(YearStart.getValue());

                    int dayInt = Integer.parseInt(day);
                    int monthInt = Integer.parseInt(month);
                    int yearInt = Integer.parseInt(year);

                    LocalDate start = LocalDate.of(yearInt,monthInt,dayInt);

                    day = String.valueOf(DayEnd.getValue());
                    month = String.valueOf(MonthEnd.getValue());
                    year = String.valueOf(YearEnd.getValue());

                    dayInt = Integer.parseInt(day);
                    monthInt = Integer.parseInt(month);
                    yearInt = Integer.parseInt(year);

                    LocalDate end = LocalDate.of(yearInt,monthInt,dayInt);

                    String Name = TaskNameTextArea.getText();
                    String Description = TaskDescriptionTextArea.getText();

                    AddTaskVerbose(Name.replace("~",""), Description.replace("~",""),start,end);

                    ReDrawText();

                    ((TaskInputDialog) self).closeDialog();
                }

            });
        }

        public void showDialog() {
            this.setVisible(true);
        }

        public void closeDialog() {
            this.dispose();
        }

    }


    public void actionPerformed(ActionEvent e) {
        if (e.getSource()==Save) {
            SaveTasks();
        }
        if (e.getSource()==Load) {
            LoadAll();
        }
        if (e.getSource()==Add) {
          InputDialog.showDialog();
        }
        if(e.getSource() == Delete){

            TaskToDelete = Integer.parseInt(JOptionPane.showInputDialog("¿Cual tarea quiere elimiar?"));

            if(tasks.size() <= 0){
                JOptionPane.showMessageDialog(null, "NO HAY TAREAS", "NO HAY TAREAS", JOptionPane.ERROR_MESSAGE);
            }
            else{

                if(TaskToDelete <= 0 || TaskToDelete > tasks.size()){
                    JOptionPane.showMessageDialog(null, "VALOR INVALIDO", "VALOR INVALIDO", JOptionPane.ERROR_MESSAGE);
                }
                else{
                    tasks.remove(TaskToDelete - 1);
                    ReDrawText();
                }

            }
        }
    }




    int Truncate(int Input, int min, int max){

        if(Input > max){
            Input = max;
        }
        if(Input < min){
            Input = min;
        }

        return Input;

    }

    void AddTask(){
        Scanner sc = new Scanner(System.in);

        String title = new String();
        String description = new String();

        Date START = new Date(0,0,0);
        Date END = new Date(0,0,0);



        System.out.println("Ingrese un titulo");

        title = sc.nextLine();

        System.out.println("Ingrese una descripción");

        description = sc.nextLine();

        System.out.println("Ingrese una fecha inicial (DÍA)");
        START.Day = sc.nextInt();
        System.out.println("Ingrese una fecha inicial (MES)");
        START.Month = sc.nextInt();
        System.out.println("Ingrese una fecha inicial (AÑO)");
        START.Year = sc.nextInt();

        System.out.println("Ingrese una fecha final (DÍA)");
        END.Day = sc.nextInt();
        System.out.println("Ingrese una fecha final (MES)");
        END.Month = sc.nextInt();
        System.out.println("Ingrese una fecha final (AÑO)");
        END.Year = sc.nextInt();


        LocalDate end = LocalDate.of(Truncate(END.Year,0,9999), Truncate(END.Month,1,12), Truncate(END.Day,1,31));
        LocalDate start = LocalDate.of(Truncate(START.Year,0,9999), Truncate(START.Month,1,12), Truncate(START.Day,1,31));

       // System.out.println("Ingrese una fecha inicial");




        System.out.println("Listo!");

        tasks.add(new Task(title, description,start,end));


    }


    public static void main(String[] args){

        Main main = new Main();
        main.Main();

    }


    public  void LoadAll(){
        try {
            File myObj = new File("Tareas.csv");
            Scanner myReader = new Scanner(myObj);
            char Line = '"';
            String Character = "" + Line;

            char Carridge = '\n';
            String CarridgeReturn = "" + Carridge;
            while (myReader.hasNextLine()) {

                String title = myReader.nextLine();
                title = title.replace("~",CarridgeReturn);
                String description = myReader.nextLine();
                description = description.replace("~",CarridgeReturn);
                String StartDate = myReader.nextLine();
                String EndDate = myReader.nextLine();

                title = title.replace(Character,"");
                description = description.replace(Character,"");

                LocalDate start = LocalDate.parse(StartDate.replace(Character,""));
                //System.out.println(StartDate.replace(Character,""));
                LocalDate end = LocalDate.parse(EndDate.replace(Character,""));

              AddTaskVerbose(title,description,start,end);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
        System.out.println("An error occurred.");
        e.printStackTrace();
        }

    }


    public  void SaveTasks(){
        if(tasks.size() <= 0){
                System.out.println("No hay tareas, el archivo no se modifico");
        }
        else{
            File file = new File("Tareas.csv");
             DateTimeFormatter myFormatObj = DateTimeFormatter.ofPattern("yyyy-MM-dd");
            try{
                FileWriter myWriter = new FileWriter("Tareas.csv");
                if(file.createNewFile()){
                     System.out.println("Archivo creado");
                }
                else{
                     System.out.println("Archivo ya existe, sobrescribiendo");
                }

                //myWriter.write();
                char Carridge = '\n';
                String CarridgeReturn = "" + Carridge;
                String Name = new String();
                String Description = new String();
                for(int i = 0; i < tasks.size(); i ++){
                //System.out.println("-------------------------------------------------------------------------");
                //System.out.println("Tarea: " + (i + 1) );
                //System.out.print("Titulo: ");
                char Line = '"';
                myWriter.write(Line);
                Name = tasks.get(i).name;
                myWriter.write(Name.replace(CarridgeReturn,"~"));
                myWriter.write(Line+"\n");
                //System.out.print("Descripción: ");

                myWriter.write(Line);
                Description = tasks.get(i).description;
                myWriter.write(Description.replace(CarridgeReturn,"~"));
                myWriter.write(Line+"\n");

                myWriter.write(Line);
                myWriter.write(tasks.get(i).Start.format(myFormatObj));
                myWriter.write(Line+"\n");

                myWriter.write(Line);
                myWriter.write(tasks.get(i).End.format(myFormatObj));
                myWriter.write(Line+"\n");

                //System.out.println("-------------------------------------------------------------------------");
                }


                myWriter.close();


            }
            catch(IOException e){
                System.out.println("ERROR ESCRIBIENDO A ARCHIVO");

            }
        }

    }





}
