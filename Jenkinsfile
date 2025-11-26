pipeline {
    agent any
    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/RakhanovaKamila/Kursova4', credentialsId: 'milkvass'
            }
        }
        
        stage('Build') {
            steps {
                script {
                    def vsWherePath = '"C:\\Program Files (x86)\\Microsoft Visual Studio\\Installer\\vswhere.exe"'
                    
                    def vsPath = bat(
                        script: "${vsWherePath} -latest -property installationPath",
                        returnStdout: true
                    ).trim()
                    
                    echo "Visual Studio found at: ${vsPath}"
                    
                    def msbuildPath = "\"${vsPath}\\MSBuild\\Current\\Bin\\MSBuild.exe\""
                    
                    bat "${msbuildPath} test_repos.sln /t:Build /p:Configuration=Release /p:Platform=x64"
                }
            }
        }
        
        stage('Test') {
            steps {
                bat "x64\\Release\\test_repos.exe --gtest_output=xml:test_report.xml"
            }
        }
    }
    
    post {
        always {
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
