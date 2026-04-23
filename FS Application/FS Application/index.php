<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Solution Application Form</title>
    <link rel="stylesheet" href="styles.css">
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f5f5f5;
            margin: 0;
            padding: 0;
            text-align: center;
        }
        .container {
            width: 80%;
            margin: auto;
            padding: 20px;
            background: white;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }
        .step {
            display: none;
        }
        .step.active {
            display: block;
        }
        .grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 20px;
            margin-top: 20px;
        }
        .option-card {
            background: #fff;
            border: 1px solid #ddd;
            padding: 20px;
            border-radius: 10px;
            text-align: center;
            cursor: pointer;
            transition: 0.3s;
        }
        .option-card:hover {
            background: #f0f0f0;
        }
        .progress-bar {
            display: flex;
            justify-content: space-between;
            list-style: none;
            padding: 0;
            margin-bottom: 20px;
        }
        .progress-bar li {
            width: 100%;
            text-align: center;
            position: relative;
        }
        .progress-bar li.active {
            color: green;
            font-weight: bold;
        }
        .counter {
            display: flex;
            justify-content: center;
            align-items: center;
        }
        .counter button {
            width: 30px;
            height: 30px;
            background: #ddd;
            border: none;
            cursor: pointer;
        }
        .counter input {
            width: 50px;
            text-align: center;
            border: 1px solid #ccc;
            margin: 0 5px;
        }
    </style>
</head>
<body>
   <div class="container">
        <ul class="progress-bar">
            <li class="active">Application Scenario</li>
            <li>Solution Select</li>
            <li>Basic Information</li>
            <li>Submit</li>
        </ul>

        <!-- Step 1: Application Scenario -->
        <div class="step active" id="step1">
            <h2>What's your solution application scenario?</h2>
            <div class="grid">
                <div class="option-card" data-next="step2">HPC Networking</div>                
            </div>
        </div>

        <!-- Step 2: Specific Scenario -->
        <div class="step" id="step2" data-prev="step1">
            <h2>What is your specific application scenario?</h2>
            <div class="grid">
                <div class="option-card" data-next="step3">InfiniBand Networking</div>
                <div class="option-card" data-next="step5">RoCE Networking</div>
            </div>
            <button class="back">Back</button>
        </div>
	<form id="multiStepForm" action="first_process.php" method='post'>
        <!-- Step 3 & 4 Combined: Solution Requirements -->
        <div class="step" id="step3" data-prev="step2">
            
	    <h2>What are your InfiniBand Networking Solution requirements?</h2>
        
        
            <div class="form-group">
                <label>Scenario *</label> 
                <div class="radio-group">
                    <input type="radio" name="scenario" value="Deep Learning"> Deep Learning
                    <input type="radio" name="scenario" value="High-performance computing"> High-performance computing
                    <input type="radio" name="scenario" value="VDI"> VDI
                    <input type="radio" name="scenario" value="Cloud scenario"> Cloud scenario
                    <input type="radio" name="scenario" value="Other"> Other
                </div>
            </div>

            <label>GPU Type:</label>
            <input type="text" name="gpu_type">
            

            <div class="form-group">
                <label>Number of GPUs *</label>
                <div class="counter">
                    <button type="button" onclick="decrease('num_gpus')">-</button>
                    <input type="number" id="num_gpus" name="num_gpus" value="1" min="1">
                    <button type="button" onclick="increase('num_gpus')">+</button>
                </div>
            </div>

            <div class="form-group">
                <label>CPU Type *</label>
                <div class="radio-group">
                    <input type="radio" name="cpu_type" value="3rd Gen Intel Xeon"> 3rd Gen Intel Xeon®
                    <input type="radio" name="cpu_type" value="4th Gen Intel Xeon"> 4th Gen Intel Xeon®
                    <input type="radio" name="cpu_type" value="5th Gen Intel Xeon"> 5th Gen Intel Xeon®
                    <input type="radio" name="cpu_type" value="AMD"> AMD
                    <input type="radio" name="cpu_type" value="Other"> Other
                </div>
            </div>

            <div class="form-group">
                <label>Operating System *</label>
                <div class="checkbox-group">
                    <input type="checkbox" name="os[]" value="Windows Server"> Microsoft Windows Server
                    <input type="checkbox" name="os[]" value="VMware ESXi"> VMware ESXi
                    <input type="checkbox" name="os[]" value="Red Hat Enterprise Linux"> Red Hat Enterprise Linux
                    <input type="checkbox" name="os[]" value="CentOS"> CentOS
                    <input type="checkbox" name="os[]" value="Other"> Other
                </div>
            </div>
            
            
        
	<h3>2. Please provide us with your InfiniBand Network business needs</h3>
	
            <div class="form-group">
                <label>Network Type *</label>
                <div class="checkbox-group">
                    <input type="checkbox" name="network_type[]" value="Computing power networking"> Computing power networking
                    <input type="checkbox" name="network_type[]" value="Storage networking"> Storage networking
                    <input type="checkbox" name="network_type[]" value="In-band networking"> In-band networking
                    <input type="checkbox" name="network_type[]" value="Out-of-band networking"> Out-of-band networking
                </div>
            </div>

            <div class="form-group">
                <label>Bandwidth Information *</label>
                <div class="checkbox-group">
                    <input type="checkbox" name="bandwidth[]" value="800G"> 800G
                    <input type="checkbox" name="bandwidth[]" value="400G"> 400G
                    <input type="checkbox" name="bandwidth[]" value="200G"> 200G
                    <input type="checkbox" name="bandwidth[]" value="100G"> 100G
                    <input type="checkbox" name="bandwidth[]" value="40G"> 40G
                    <input type="checkbox" name="bandwidth[]" value="Other"> Other
                </div>
            </div>

            <div class="form-group">
                <label>Number of Servers *</label>
                <div class="counter">
                    <button type="button" onclick="decrease('num_servers')">-</button>
                    <input type="number" id="num_servers" name="num_servers" value="1" min="1">
                    <button type="button" onclick="increase('num_servers')">+</button>
                </div>
            </div>

            <div class="form-group">
                <label>Other Requirements</label>
                <input type="text" name="other_requirements" placeholder="Enter more details">
            </div>

            <h2>3. Leave a message for other project descriptions in detail</h2>
            <textarea name="project_description" rows="4" placeholder="We are capable of working out a professional solution to maximize the utilization of the equipment and link resources also to save costs and improve business reliability."></textarea>
            
            <div class="form-group">
                <label>Upload File</label>
                <input type="file" name="file_upload">
            </div>
	    <textarea name="other_requirements2" rows="4"></textarea>
            
            
        
	

           

            

            

         
	    

            

            <div class="button-group">
                <button class="back">Back</button>
            <button class="next" onclick="nextSection('q2.php')" data-next="step4">Next</button>
            </div>
       <!-- /form -->
            
        </div>

	<div class="step" id="step5" data-prev="step2">
	
	    <h2>What are your RoCE Networking Solution requirements?</h2>
        <p><strong>1. Please provide us with your RoCE Network application scenarios and basic needs</strong></p>
        
        
	<div class="form-group">
            <label>Scenario *</label>
            <div class="checkbox-group">
                <label><input type="radio" name="scenario2" value="Deep Learning"> Deep Learning</label>
                <label><input type="radio" name="scenario2" value="High-performance computing"> High-performance computing</label>
                <label><input type="radio" name="scenario2" value="Data center"> Data center</label>
                <label><input type="radio" name="scenario2" value="Cloud scenario"> Cloud scenario</label>
                <label><input type="radio" name="scenario2" value="Other"> Other</label>
            </div>
        </div>
        
        <div class="form-group">
            <label>NIC Speed *</label>
            <input type="text" name="nic_speed" placeholder="Enter more details">
        </div>
        
        <div class="form-group">
            <label>Number of NICs</label>
            <div class="counter">
                <button type="button" onclick="decrease('num_nics')">-</button>
                <input type="number" id="num_nics" name="num_nics" value="1" min="1">
                <button type="button" onclick="increase('num_nics')">+</button>
            </div>
        </div>
        
        <div class="form-group">
            <label>NIC Type</label>
            <input type="text" name="nic_type" placeholder="Enter more details">
        </div>
        
        <div class="form-group">
            <label>Operating System *</label>
            <div class="checkbox-group">
                <label><input type="checkbox" name="os2[]" value="Microsoft Windows Server"> Microsoft Windows Server</label>
                <label><input type="checkbox" name="os2[]" value="VMware ESXi"> VMware ESXi</label>
                <label><input type="checkbox" name="os2[]" value="Red Hat Enterprise Linux"> Red Hat Enterprise Linux</label>
                <label><input type="checkbox" name="os2[]" value="CentOS"> CentOS</label>
                <label><input type="checkbox" name="os2[]" value="Other"> Other</label>
            </div>
        </div>
        
        <div class="form-group">
            <label>Switch Management Platform</label>
            <input type="text" name="SMP" placeholder="Enter more details">
        </div>
	<p><strong>2. Please provide us with your ROCE Network business needs</p>
        
            <div class="form-group">
                <label>Network Type *</label><br>
                <input type="checkbox" name="network_type2[]" value="Spine"> Spine
                <input type="checkbox" name="network_type2[]" value="Leaf"> Leaf
                <input type="checkbox" name="network_type2[]" value="Server"> Server
                <input type="checkbox" name="network_type2[]" value="Other"> Other
            </div>
            <div class="form-group">
                <label>Bandwidth Information *</label><br>
                <input type="checkbox" name="bandwidth_info[]" value="400G"> 400G
                <input type="checkbox" name="bandwidth_info[]" value="200G"> 200G
                <input type="checkbox" name="bandwidth_info[]" value="100G"> 100G
                <input type="checkbox" name="bandwidth_info[]" value="40G"> 40G
                <input type="checkbox" name="bandwidth_info[]" value="Other"> Other
            </div>
            <div class="form-group">
                <label>Expected Convergence Ratio</label><br>
                <input type="text" name="Expected" placeholder="Enter more details">
            </div>
            <div class="form-group">
                <label>Other Equipment Requirements</label><br>
                <input type="checkbox" name="Other_ER[]" value="Server"> Server
                <input type="checkbox" name="Other_ER[]" value="Switching"> Switching
                <input type="checkbox" name="Other_ER[]" value="Optical Transceivers"> Optical Transceivers
                <input type="checkbox" name="Other_ER[]" value="Cables"> Cables
            </div>
            <div class="form-group">
                <label>Leave a message for other project descriptions in detail</label>
                <textarea name="TBox1" placeholder="We are capable of working out a professional solution to maximize the utilization of the equipment..."></textarea>
            </div>
            <div class="form-group">
                <label>Upload File</label>
                <input type="file" name="file_upload2">
            </div>
            <div class="button-group">
                <button class="back">Back</button>
            	<button class="next" onclick="nextSection('q3.php')" data-next="step4">Next</button>
            </div>
        
	</div>

        <!-- Step 5: Submit -->
        <div class="step" id="step4">
	    <!-- form method = "post" action = "q2.php" -->
            <h2>Tell us a little about yourself</h2>
        
        
            <div class="form-row">
                <div class="form-group">
                    <label>First name *</label>
                    <input type="text" name="first_name" required>
                </div>
                <div class="form-group">
                    <label>Last name *</label>
                    <input type="text" name="last_name" required>
                </div>
            </div>

            <div class="form-row">
                <div class="form-group">
                    <label>Business email *</label>
                    <input type="email" name="email" required>
                </div>
                <div class="form-group">
                    <label>Company name *</label>
                    <input type="text" name="company_name" required>
                </div>
            </div>

            <div class="form-row">
                <div class="form-group">
                    <label>Country</label>
                    <select name="country">
                        <option>United States</option>
                        <option>Canada</option>
                        <option>United Kingdom</option>
                        <option>Other</option>
                    </select>
                </div>
                <div class="form-group">
                    <label>State/Province/Region</label>
                    <select name="state">
                        <option>Armed Forces Americas</option>
                        <option>Armed Forces Europe</option>
                        <option>California</option>
                        <option>Other</option>
                    </select>
                </div>
            </div>

            <div class="form-row">
                <div class="form-group">
                    <label>Phone number *</label>
                    <div class="form-row">
                        <select name="phone_code">
                            <option>+1</option>
                            <option>+44</option>
                            <option>+91</option>
                            <option>Other</option>
                        </select>
                        <input type="text" name="phone_number" required>
                    </div>
                </div>
                <div class="form-group">
                    <label>Industry</label>
                    <select name="industry">
                        <option>Telecom</option>
                        <option>IT</option>
                        <option>Healthcare</option>
                        <option>Other</option>
                    </select>
                </div>
            </div>

            <div class="form-group">
                <label>Job title</label>
                <input type="text" name="job_title">
            </div>

            <p class="privacy-text">
                By clicking the "Submit", you agree that your information is collected and used for the purpose of responding to your inquiry in accordance with the <a href="#">Privacy Policy</a> and <a href="#">Terms of Use</a>.
            </p>
            
            <div class="button-group">
                <button class="back">Back</button>
                <button type="submit" class="submit-button">Submit</button>
            </div>
	    
        </div>
        </form>
    </div>
    <script>
	function nextSection(newAction) {
		document.getElementById("multiStepForm").action = newAction;
	}
	function increase(id) {
        let input = document.getElementById(id);
        input.value = parseInt(input.value) + 1;
    	}

    function decrease(id) {
        let input = document.getElementById(id);
        if (input.value > 1) {
            input.value = parseInt(input.value) - 1;
        }
    }

    document.addEventListener("DOMContentLoaded", function () {
    const steps = document.querySelectorAll(".step");
    const optionCards = document.querySelectorAll(".option-card");
    const nextButtons = document.querySelectorAll(".next");
    const backButtons = document.querySelectorAll(".back");

    let prevStep4ID = null; // Store previous step before step4

    // Handle option card clicks
    optionCards.forEach(card => {
        card.addEventListener("click", function () {
            steps.forEach(step => step.classList.remove("active"));
            const nextStep = document.getElementById(this.dataset.next);
            if (nextStep.id === "step4") {
                prevStep4ID = this.closest(".step").id;
            }
            nextStep.classList.add("active");
        });
    });

    // Handle next button clicks
    nextButtons.forEach(button => {
        button.addEventListener("click", function () {
            const currentStep = this.closest(".step");
            steps.forEach(step => step.classList.remove("active"));
            const nextStep = document.getElementById(this.dataset.next);
            if (nextStep.id === "step4") {
                prevStep4ID = currentStep.id;
            }
            nextStep.classList.add("active");
        });
    });

    // Handle back button clicks
    backButtons.forEach(button => {
        button.addEventListener("click", function () {
            const currentStep = Array.from(steps).find(step => step.classList.contains("active"));
            let prevStepId = currentStep.getAttribute("data-prev");
            
            // Dynamically set the back button for step4
            if (currentStep.id === "step4" && prevStep4ID) {
                prevStepId = prevStep4ID;
            }

            if (prevStepId) {
                steps.forEach(step => step.classList.remove("active"));
                document.getElementById(prevStepId).classList.add("active");
            }
        });
    });
});
    </script>
</body>
</html>
