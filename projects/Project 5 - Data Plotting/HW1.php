<!DOCTYPE html>

<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8" />
    <title>Richard Angueira CPS4721 HW1</title>
</head>
<body>
<?php include("dbconfig.php"); ?>
    <h2>Richard Angueira</h2>
    <h3>CPS 4721 - HW1</h3>

    <p>1. Views and tables in database play different roles in data mining. Please give two real-world examples based on the attributes in the uszips table in details when to use a view and a table for data mining.</p>
    <ul>
        <li>A <b>Table</b> is the primary unit of storage in a database. The uszips table is filled with an enormous amount of information and will require a more robust form of data manipulation.
        <li>A <b>View</b> is a virtual table that runs a specific <b>SELECT</b> statement. Views are better used in public setting when speed and security are required. The uszips table has 86 attributes and a few of those attributes contain sensitive information,
            such as:  [race_white], [race_black], [income_household_six_figure, military].</li>
    </ul>
    
    <p>2. Give 4 examples in real-world based on the attributes in the uszips table that show the difference between a SQL report and data mining.</p>
    <ul>
        <li>SQL reporting takes a more historical approach to data management. It is still helpful for gathering information like a cities [population] and [state_names]. It can even help to discover patterns and trends.</li>
        <li>Data mining do a better job at discovering the relationship between different attributes, such as the way a cities [population] can affect its [unemployment_rate]</li>
        <li>Both sql reporting and datamining excel in data visualization. SQL reorting does well to get the detailed numbers in front of users quickly, while data mining can show the correlation between all areas of business.</li>
    </ul>
    <p>3. Show the zipcode of the richest zipcode for each state based on Median household income. The output should have (zipcode, city, state, population, income) that sorted by the state name.</p>
    <ul>
        <li><?php 
            
            $sql = "select zip as zipcode, city, state_name as state, population, income_household_median as income from datamining.uszips where income_household_median in (select max(income_household_median) from datamining.uszips group by datamining.uszips.state_name) order by datamining.uszips.state_name";
            $result = mysqli_query($conn, $sql);

            if (mysqli_num_rows($result) > 0) {
            // output data of each row
                echo "<table border = '1'> <tr><th>Zipcode</th><th>City</th><th>State</th><th>Population</th><th>Income</th>";
            while($row = mysqli_fetch_assoc($result)) {
                echo "<tr>";
                echo "<td>" . $row["zipcode"]. "</td>";
                echo "<td>" . $row["city"]. "</td>";
                echo "<td>" . $row["state"]. "</td>";
                echo "<td>" . $row["population"]. "</td>";
                echo "<td>" . $row["income"]. "</td>";
                echo "</tr>";
            }
            echo "</table>";
            } else {
            echo "0 results";}

            //SQL code used to create the tables

            //<li><b>To create table:</b> create table HW1_rangueir (state varchar(50), population float, NumofZipcode float, health_uninsured float, total_education_college_or_above float);</li>
            //<li><b>To add values to new table:</b> insert into HW1_rangueir(state, population, NumofZipcode, health_uninsured, total_education_college_or_above) select datamining.uszips.state_name, sum(datamining.uszips.population), count(datamining.uszips.zip), avg(datamining.uszips.health_uninsured), avg(datamining.uszips.education_college_or_above) from datamining.uszips group by datamining.uszips.state_name;</li>
            //<li><b>Created a temp table called tmp1 to hold the averages for each state:</b> create table tmp1 (state varchar(50), average float not null);</li>
            //<li><b>To add values to new column:</b> update HW1_rangueir h, tmp1 t set h.avg_income = t.average where h.state = t.state;</li>
            //<li><b>Add two more columns for state_name and area:</b> alter table HW1_rangueir add (state_name varchar(50) not null, area float not null);</li>
            //<li><b>To add values to new column:</b> update HW1_rangueir h, USstateData u set h.area = u.area, h.state_name = u.name where h.state = u.name;</li>
            //<li><b>To add a new column:</b> alter table HW1_rangueir add avg_income float not null;</li>
            //<li><b>Add one more column for density:</b> alter table HW1_rangueir add (density float not null);</li>
            //<li><b>Created new temp table called USstateData:</b> create table USstateData(state varchar(2), name varchar(50), area float not null);</li>
            //<li><b>Calculate density:</b> update HW1_rangueir h set h.density = h.population/h.area where h.state = h.state_name;</li>
            
            ?>
        </li>
    </ul>
    <p>4. create a table HW1_xxxx with columns (state, population, NumofZipcode, health_uninsured, ) that has the total population, the number of zip code (NumofZipcode), total health_uninsured population, 
        total education_college_or_above population of each state and DC. Note: The original data of health_uninsured and education_college_or_above are ratios, NOT size.</p>
    <ul>
        <li>View the HW1.php file to all the sql statments used to create the tables. lines 51 - 60.</li>
    </ul>
    <p>5. Add a new column to your HW1_xxxx table - avg_income to store the average Median household income of each state and DC.</p>
    <ul>
        <li>View the HW1.php file to all the sql statments used to create the tables. lines 51 - 60.</li>
       
    </ul>
    <p>6. Add two more columns to your HW1_xxxx table - state name and area by loading the data file US_state_data.csv. You may need to create a temporary table first.</p>
    <ul>
        <li>View the HW1.php file to all the sql statments used to create the tables. lines 51 - 60.</li>
    </ul>
    <p>7. Please display your HW1_xxx data with density for each state and DC on the browser. Note: density = population/area. The result should sorted by the state name.</p>
    <ul>
        <li><?php 
            
            $sql = "select * from HW1_rangueir where population is not null";
            $result = mysqli_query($conn, $sql);

            if (mysqli_num_rows($result) > 0) {
            // output data of each row
                echo "<table border = '1'> <tr><th>State</th><th>Population</th><th>Number of Zipcodes</th><th>Health Uninsured</th><th>Total Education: College or above</th><th>Average Income</th><th>State Name</th><th>Area</th><th>Density</th>";
            while($row = mysqli_fetch_assoc($result)) {
                echo "<tr>";
                echo "<td>" . $row["state"]. "</td>";
                echo "<td>" . $row["population"]. "</td>";
                echo "<td>" . $row["NumofZipcode"]. "</td>";
                echo "<td>" . $row["health_uninsured"]. "</td>";
                echo "<td>" . $row["total_education_college_or_above"]. "</td>";
                echo "<td>" . $row["avg_income"]. "</td>";
                echo "<td>" . $row["state_name"]. "</td>";
                echo "<td>" . $row["area"]. "</td>";
                echo "<td>" . $row["density"]. "</td>";
                echo "</tr>";
            }
            echo "</table>";
            } else {
            echo "0 results";}
            ?></li>
    </ul>
    <p>8. Select 3 attributes (A, B, C) from your HW1 table, and identify which two attributes might be most related based on the correlation values among the 50 states and DC.</p>
    <ul>
        <li>A = Total Education | B = Density | C = Average Income</li>
        
        <li><?php $sql1 = "select (avg(total_education_college_or_above * density) - avg(total_education_college_or_above) * avg(density)) / (sqrt(avg(total_education_college_or_above * total_education_college_or_above) - avg(total_education_college_or_above) * avg(total_education_college_or_above)) * sqrt(avg(density * density) - avg(density) * avg(density))) AS correlation from HW1_rangueir;";
            $result1 = mysqli_query($conn, $sql1); 
            $row1 = $result1->fetch_array()[0] ?? '';
            echo "The correlation between (A,B): " . $row1;?></li>
        <li><?php $sql2 = "select (avg(total_education_college_or_above * avg_income) - avg(total_education_college_or_above) * avg(avg_income)) / (sqrt(avg(total_education_college_or_above * total_education_college_or_above) - avg(total_education_college_or_above) * avg(total_education_college_or_above)) * sqrt(avg(avg_income * avg_income) - avg(avg_income) * avg(avg_income))) AS correlation from HW1_rangueir;";
            $result2 = mysqli_query($conn, $sql2); 
            $row2 = $result2->fetch_array()[0] ?? '';
            echo "The correlation between (A,C): " . $row2;?></li>
        <li><?php $sql3 = " select (avg(density * avg_income) - avg(density) * avg(avg_income)) / (sqrt(avg(density * density) - avg(density) * avg(density)) * sqrt(avg(avg_income * avg_income) - avg(avg_income) * avg(avg_income))) AS correlation from HW1_rangueir;";
            $result3 = mysqli_query($conn, $sql3); 
            $row3 = $result3->fetch_array()[0] ?? '';
            echo "The correlation between (B,C): " . $row3;?></li>
        <li>The highest correlation were between Total Education College or above/Density(A,B) and Total Education College or above/Average Income(A,C)</li>
        <li>It is easy to understand how higher education can lead to higher income. It is intersting to see that higher education also has a significant effect on the population density, although I suppose larger cities also house and employ educated individuals.</li>
    </ul>
</body>
</html>