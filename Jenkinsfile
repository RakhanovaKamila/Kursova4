pipeline {
    agent any

    environment {
        NUGET_PATH = 'C:\\Users\\user\\Tools\\nuget.exe'
        MSBUILD_PATH = 'C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe'
    }

    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/RakhanovaKamila/Kursova4', 
                    branch: 'master',
                    credentialsId: 'milkvass'
            }
        }

        stage('Build') {
            steps {
                bat '''
                    rmdir /s /q packages 2>nul || echo "No packages folder"
                    "%NUGET_PATH%" restore test_repos.sln
                    "%MSBUILD_PATH%" test_repos.sln /t:Build /p:Configuration=Release
                '''
            }
        }

        stage('Test') {
            steps {
                bat 'x64\\Release\\test_repos.exe --gtest_output=xml:test_report.xml'
            }
        }
    }

    post {
        always {
            junit 'test_report.xml'
        }
    }
}
