pipeline {
    agent any
    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/RakhanovaKamila/Kursova4', credentialsId: 'milkvass'
            }
        }
        
        stage('Restore NuGet Packages') {
            steps {
                script {
                    // Check if nuget.exe exists, if not download it
                    def nugetExists = fileExists('nuget.exe')
                    if (!nugetExists) {
                        echo 'Downloading nuget.exe...'
                        powershell '''
                            Invoke-WebRequest -Uri "https://dist.nuget.org/win-x86-commandline/latest/nuget.exe" -OutFile "nuget.exe"
                        '''
                    }
                    // Restore packages
                    bat 'nuget.exe restore test_repos.sln'
                }
            }
        }
        
        stage('Build') {
            steps {
                // Build the project using the discovered MSBuild path
                bat '"C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe" test_repos.sln /t:Build /p:Configuration=Release /p:Platform=x64'
            }
        }
        
        stage('Test') {
            steps {
                // Run Google Test executable and generate XML report
                bat "x64\\Release\\test_repos.exe --gtest_output=xml:test_report.xml"
            }
        }
    }
    
    post {
        always {
            // Publish test results using JUnit plugin
            junit allowEmptyResults: true, testResults: 'test_report.xml'
        }
        success {
            echo 'Pipeline completed successfully!'
        }
        failure {
            echo 'Pipeline failed. Check the logs for details.'
        }
    }
}
