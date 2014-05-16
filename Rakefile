require 'yaml'
require 'xcodeproj'

APP_NAME = 'V.S.SHOOTER'
BUILD_CONFIFURATION = 'Release'
CODE_SIGN_IDENTITY = 'iPhone Distribution'
KEYCHAIN_NAME = "ios-build.keychain"

WORKING_DIRECTORY = `pwd`.chomp
WORKSPACE_PATH = "#{WORKING_DIRECTORY}/#{APP_NAME}.xcworkspace"

CONFIG_YML = File.exists?("#{WORKING_DIRECTORY}/config.yml") ? YAML.load_file("#{WORKING_DIRECTORY}/config.yml") : nil

project = Xcodeproj::Project.open("#{WORKING_DIRECTORY}/proj.ios_mac/#{APP_NAME}.xcodeproj")
SCHEME = project.targets.find{|elem| elem.name == APP_NAME << " iOS"}
APP_SCREEN_NAME = SCHEME.product_reference.display_name

PROVISIONING_PROFILES_PATH = "#{Dir.home}/Library/MobileDevice/Provisioning Profiles"
LOCAL_PROVISIONING_PROFILES_PATH = "#{WORKING_DIRECTORY}/Provisioning_Profile"
APP_DST_PATH = "#{WORKING_DIRECTORY}/build_app/#{BUILD_CONFIFURATION}"


desc "bundle install"
task :setup do
  sh 'bundle install'
  sh 'bundle exec pod install'
end

desc "Run unit test"
task :utest => [:setup] do
  if ENV['TRAVIS']
    destination = '"name=iPhone Retina (3.5-inch),OS=7.0"'
  else
    destination = '"name=iPhone Retina (3.5-inch),OS=7.1"'
  end

  sh "xcodebuild -workspace #{WORKSPACE_PATH} -scheme #{SCHEME.name} -destination #{destination} test | xcpretty -c; exit ${PIPESTATUS[0]}"
end

task :build_ipa => [:setup, :utest, :download_provisioning_profiles] do
  remove_dir(APP_DST_PATH) if File.exists?(APP_DST_PATH)

  adhoc_provisioning_path = "#{PROVISIONING_PROFILES_PATH}/#{adhoc_mobileprovision_file_name}"

  add_certificates
  sh "xcodebuild -workspace #{WORKSPACE_PATH} -scheme #{SCHEME.name} -sdk #{SCHEME.sdk} -configuration #{BUILD_CONFIFURATION} CODE_SIGN_IDENTITY='#{CODE_SIGN_IDENTITY}' CONFIGURATION_TEMP_DIR=#{APP_DST_PATH}/tmp CONFIGURATION_BUILD_DIR=#{APP_DST_PATH} clean build | xcpretty -c; exit ${PIPESTATUS[0]}"
  sh "xcrun -sdk #{SCHEME.sdk} PackageApplication #{APP_DST_PATH}/#{APP_SCREEN_NAME} -o #{APP_DST_PATH}/#{APP_NAME}.ipa -embed #{adhoc_provisioning_path}"
  sh "zip -r #{APP_DST_PATH}/#{APP_SCREEN_NAME}.dSYM.zip #{APP_DST_PATH}/#{APP_SCREEN_NAME}.dSYM"
  remove_certificates
end

desc "Upload to TestFlight"
task :testflight => [:build_ipa] do
   if ENV['TRAVIS'] and ENV['TRAVIS_PULL_REQUEST'] != "false"
    puts "This is a pull request. No deployment will be done."
    next
  end
  if ENV['TRAVIS'] and ENV['TRAVIS_BRANCH'] != "master"
    puts "Testing on a branch other than master. No deployment will be done."
    next
  end
  testflight_api_token = CONFIG_YML.nil? ? ENV['TESTFLIGHT_API_TOKEN'] : CONFIG_YML['testflight']['api_token']
  testflight_team_token = CONFIG_YML.nil? ? ENV['TESTFLIGHT_TEAM_TOKEN'] : CONFIG_YML['testflight']['team_token']
  sh "curl http://testflightapp.com/api/builds.json" \
    " -F file=@#{APP_DST_PATH}/#{APP_NAME}.ipa" \
    " -F dsym=@#{APP_DST_PATH}/#{APP_SCREEN_NAME}.dSYM.zip" \
    " -F api_token=#{testflight_api_token}" \
    " -F team_token=#{testflight_team_token}" \
    " -F notes='This build was uploaded via the upload API'" \
    " -F notify=True" \
    " -F distribution_lists='AllTeammatesDistributionList'"
end

task :download_provisioning_profiles do
  FileUtils.rm(Dir.glob("#{PROVISIONING_PROFILES_PATH}/*"))

  apple_dev_center_id = CONFIG_YML.nil? ? ENV['APPLE_DEV_CENTER_ID'] : CONFIG_YML['apple_dev_center']['id']
  apple_dev_center_pass = CONFIG_YML.nil? ? ENV['APPLE_DEV_CENTER_PASS'] : CONFIG_YML['apple_dev_center']['pass']
  sh "bundle exec apple_dev_center.rb -u #{apple_dev_center_id} -p #{apple_dev_center_pass} -d #{LOCAL_PROVISIONING_PROFILES_PATH} -O /dev/null"
end

def add_certificates
  decrypt_certificates
  certificates_pass = CONFIG_YML.nil? ? ENV['CERTIFICATES_PASS'] : CONFIG_YML['apple_dev_center']['certificates']['pass']

  sh "security create-keychain -p travis #{KEYCHAIN_NAME}"
  sh "security default-keychain -s ios-build.keychain"
  sh "security unlock-keychain -p travis ios-build.keychain"
  sh "security import #{WORKING_DIRECTORY}/certificates/AppleWWDRCA.cer -k ~/Library/Keychains/#{KEYCHAIN_NAME} -T /usr/bin/codesign"
  sh "security import #{WORKING_DIRECTORY}/certificates/dist.cer -k ~/Library/Keychains/#{KEYCHAIN_NAME} -T /usr/bin/codesign"
  sh "security import #{WORKING_DIRECTORY}/certificates/dist.p12 -k ~/Library/Keychains/#{KEYCHAIN_NAME} -P #{certificates_pass} -T /usr/bin/codesign > /dev/null 2>&1"
  
  # specifies no timeout
  sh "security set-keychain-settings '#{KEYCHAIN_NAME}'"

  sh "mkdir -p '#{PROVISIONING_PROFILES_PATH}'"
  sh "cp '#{adhoc_mobileprovision_path}' '#{PROVISIONING_PROFILES_PATH}'"
end

def decrypt_certificates
  p12_pass = CONFIG_YML.nil? ? ENV['AES_P12_PASS'] : CONFIG_YML['p12_pass']
  cer_pass = CONFIG_YML.nil? ? ENV['AES_CER_PASS'] : CONFIG_YML['cer_pass']

  sh "openssl aes-256-cbc -k #{p12_pass} -in ./certificates/dist.p12.enc -d -a -out ./certificates/dist.p12"
  sh "openssl aes-256-cbc -k #{cer_pass} -in ./certificates/dist.cer.enc -d -a -out ./certificates/dist.cer"
end

def remove_certificates
  sh "security delete-keychain #{KEYCHAIN_NAME}"
  FileUtils.rm("#{PROVISIONING_PROFILES_PATH}/#{adhoc_mobileprovision_file_name}")
end

def adhoc_mobileprovision_path
  Dir.glob("#{LOCAL_PROVISIONING_PROFILES_PATH}/*_adhoc.mobileprovision")[0]
end

def adhoc_mobileprovision_file_name
  File::basename(adhoc_mobileprovision_path)
end